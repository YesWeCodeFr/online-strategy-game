// container.ts
class Container {
    private services: { [key: string]: any } = {};

    register<T>(name: string, instance: T): void {
        this.services[name] = instance;
    }

    get<T>(name: string): T {
        const service = this.services[name];
        if (!service) {
            throw new Error(`Service ${name} not found`);
        }
        return service;
    }
}

const container = new Container();
export default container;